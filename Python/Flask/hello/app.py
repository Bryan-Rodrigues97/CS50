from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet", methods=["GET", "POST"])
def greet():
    if request.method == "GET":
        # request.args is a dictionary that contains the parameters sended by the user using the method get
        name = request.args.get("name", "world")
    elif request.method == "POST":
        # with POST, use request.form
        name = request.form.get("name", "world")

    return render_template("greet.html", name=name)
