import math


def grade(sentence):
    letters = 0
    sentences = 0
    words = 1

    for char in sentence:
        if char == " ":
            words += 1
        if char in [".", "?", "!"]:
            sentences += 1
        if char.isalpha():
            letters += 1

    L = (letters / words) * 100
    S = (sentences / words) * 100

    return 0.0588 * L - 0.296 * S - 15.8


def main():
    sentence = input("Text: ")
    result = round(grade(sentence))

    if result > 15:
        print("Grade 16+")
    elif result < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {result}")


main()
