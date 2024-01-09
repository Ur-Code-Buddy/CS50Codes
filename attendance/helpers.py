from flask import redirect, render_template, session, jsonify
from functools import wraps
from cs50 import SQL
from werkzeug.security import check_password_hash, generate_password_hash
import secrets





# Rest of the code remains unchanged
def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code

def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function

def admin_required(func):
    @wraps(func)
    def decorated_view(*args, **kwargs):
        # Check if the current user is an admin
        if not is_admin():
            # If not, abort with a 403 Forbidden error

            print(f"Permission Denied, User: {session.get('user_id')} tried to access it")
            response = {"message": "Not Accepted,not an ADMIN"}
            return jsonify(response)


        # If the user is an admin, proceed with the original view function
        return func(*args, **kwargs)

    return decorated_view


def is_admin():
    # Retrieve the user ID from the session
    user_id = session.get("user_id")

    # Assuming you have a 'users' table with an 'is_admin' column
    user = SQL("sqlite:///users.db").execute("SELECT is_admin FROM users WHERE id = ?", user_id)

    # Check if the user exists and is an admin
    return user and user[0]["is_admin"] == 'TRUE'
