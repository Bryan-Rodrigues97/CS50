import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

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
    rows = db.execute('SELECT stock_name, stock_share FROM user_wallet WHERE user_id = ?', session["user_id"])
    totalQty = 0
    totalAmount = 0

    for row in rows:
        price = lookup(row["stock_name"])["price"]
        row["currentPrice"] = price
        row["amount"] = price * row["stock_share"]

        totalQty = totalQty + row["stock_share"]
        totalAmount = totalAmount + row["amount"]

    rows.append({"stock_name": "totals", "stock_share": totalQty, "currentPrice": 0, "amount": totalAmount})

    # Grand Total
    user_row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    balance = user_row[0]["cash"]

    return render_template("index.html", stocks=rows, balance=round(balance, 2), grand_total = round(balance + totalAmount, 2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    if not request.form.get("name"):
        return apology("Must provide a stock Symbol")

    stock = lookup(request.form.get("name"))
    if stock == None:
        return apology(f"Cannot find the stock {request.form.get("name")}")

    if not request.form.get("shares"):
        return apology(f"Cannot find the stock {request.form.get("name")}")
    else:
        try:
            shares = int(request.form.get("shares"))

            # Query database for available Cash
            rows = db.execute("SELECT * FROM users WHERE id = ?",  session["user_id"])

            # Ensure username exists
            if len(rows) != 1:
                return apology("Oops, cannot buy shares. Please, check your login account!")

            # Ensure the user has balance to buy a stock
            balance = float(rows[0]["cash"])

            if balance < shares * stock["price"]:
                #flash("Insufficient balance to complete the transaction")
                return apology("Insufficient balance to complete the transaction")
            else:
                db.execute("INSERT INTO user_transactions (user_id, stock_name, stock_share, stock_value) values (?,?,?,?)", session["user_id"], stock["symbol"], shares, stock["price"])
                db.execute("UPDATE users SET cash = ?", balance - shares * stock["price"])

                wallet = db.execute("SELECT * FROM user_wallet WHERE user_id = ? AND stock_name = ?", session["user_id"], stock["symbol"])

                if len(wallet) == 0:
                    db.execute("INSERT INTO user_wallet (user_id, stock_name, stock_share) VALUES (?,?,?)", session["user_id"], stock["symbol"], shares)
                else:
                    db.execute("UPDATE user_wallet SET stock_share = ? WHERE user_id = ? AND stock_name = ?", wallet[0]["stock_share"] + shares, session["user_id"], stock["symbol"])

                #flash("Success! Check the history page to see details!")
                return redirect("/")
        except:
            return apology("Oops, cannot buy shares. Please, try again!")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM user_transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=rows)


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
    if request.method == "GET":
        return render_template("quote.html")

    if not request.form.get("name"):
        return apology("Must provide a stock Symbol")

    stock = lookup(request.form.get("name"))
    if stock == None:
        return apology(f"Cannot find the stock {request.form.get("name")}")
    return render_template("quoted.html", symbol = stock["symbol"], price = stock["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    # User reached route via POST (as by submitting a form via POST)
    else:
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
        if len(rows) != 0 :
            return apology(f"Username {request.form.get("username")} already exists!", 403)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?,?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

            # Remember which user has logged in
            session["user_id"] = request.form.get("username")

            # Redirect user to home page
            return redirect("/")
        except:
            return apology("Cannot register. Pelase, try again!")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    else:
        # TODO - Sell stock when the request is method POST
        return render_template("sell.html")
