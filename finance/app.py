import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol ",
        user_id,
    )

    user_cash_db = db.execute("SELECT cash FROM users WHERE id= ?", user_id)
    cash = user_cash_db[0]["cash"]

    total_value = grand_total = cash
    for stock in stocks:
        quote = lookup(stock["symbol"])

        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    return render_template(
        "portfolio.html",
        stocks=stocks,
        cash=cash,
        total_value=total_value,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Symbol error")
        stock = lookup(symbol)
        if not stock:
            return apology("Symbol error")
        if not shares or not shares.isdigit() or int(shares) < 0:
            return apology("Share Not Available")

        cost_needed = int(shares) * stock["price"]
        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        print(user_cash)
        if cost_needed > user_cash:
            return apology("Not enough Funds")

        new_cash = user_cash - cost_needed
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, price, shares, datetime) VALUES (?,?,?,?,?)",
            user_id,
            stock["symbol"],
            stock["price"],
            shares,
            datetime.now(),
        )
        flash("Bought!")

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY datetime DESC", user_id
    )
    return render_template("history.html", rows=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol error")
        stock = lookup(symbol)
        if not stock:
            return apology("Symbol error")

        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # checking if the values are acceptable
        if not username:
            return apology("Username Error")
        if not password:
            return apology("Password Error")
        if not confirmation:
            return apology("Confirmation Error")

        if password != confirmation:
            return apology("Password and Confirmation DO NOT MATCH")

        print("All went good")
        # saving it as a hashed pass in db
        hash = generate_password_hash(password)

        try:
            new_user = db.execute(
                "INSERT INTO users (username,hash) VALUES(?,?)", username, hash
            )
        except:
            return apology("Username Already Exists")

        session["user_id"] = new_user
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Symbol error")

        stock = lookup(symbol)
        if not stock:
            return apology("Symbol error")
        if not shares or not shares.isdigit() or int(shares) < 0:
            return apology("Share Not Available")

        cost_needed = int(shares) * stock["price"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        user_shares = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol,
        )
        real_shares = user_shares[0]["shares"]
        print("check 236", real_shares)

        if int(shares) > real_shares or real_shares < 0:
            return apology("Not enough Shares")

        new_cash = user_cash + cost_needed

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, price, shares, datetime) VALUES (?,?,?,?,?)",
            user_id,
            stock["symbol"],
            stock["price"],
            -int(shares),
            datetime.now(),
        )
        flash("Sold!")

        return redirect("/")

    else:
        symbols = db.execute(
            "SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", user_id
        )
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols])


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Buy shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        cash = request.form.get("cash")

        if not cash or int(cash) < 0:
            return apology("cash error")

        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_initial_cash = user_cash_db[0]["cash"]

        new_cash = user_initial_cash + int(cash)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
        flash("Cash Added!")

        return redirect("/")

    else:
        return render_template("add_cash.html")
