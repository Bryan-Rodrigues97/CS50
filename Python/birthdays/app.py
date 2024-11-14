import os
from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# Function to validate if the given Month and Day form a valid date
def validate_date(month, day):
    try:
        datetime(year=2024, month=int(month), day=int(day))
        return True
    except:
        print("Erro")
        return False

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if name and month and day:
            if validate_date(month, day):
                db.execute("INSERT INTO birthdays (name, day, month) VALUES(?, ?, ?)", name, day, month)
        return redirect("/")
    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route("/delete/<id>", methods=["POST"])
def delete(id):
    db.execute("DELETE FROM birthdays where id = ?", id)
    return redirect("/")

@app.route("/update/<id>", methods=["POST"])
def update(id):
    data = request.json
    month = data.get("month")
    day = data.get("day")

    if month and day:
        if validate_date(month, day):
            db.execute("UPDATE birthdays SET month = ?, day = ? WHERE id = ?", month, day, id)
            return "Update successful"

    return "Update failed"
