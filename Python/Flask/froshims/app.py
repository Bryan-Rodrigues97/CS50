from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = ["Soccer", "Basketball", "Ultimate Frisbee", "Rugby", "Tennis"]
SHIFTS = ["Morning", "Afternoon"]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS, shifts=SHIFTS)


@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    sport = request.form.get("sport")

    # Checks for name and sports
    if not name or sport not in SPORTS:
        return render_template("failure.html")

    # Checks for shift
    if not request.form.getlist("shift"):
        return render_template("failure.html")
    else:
        for shift in request.form.getlist("shift"):
            if shift not in SHIFTS:
                return render_template("failure.html")


    return render_template("success.html", name=name, sport=sport)
