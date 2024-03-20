from flask import Flask, request, render_template, redirect
import csv
import os

app = Flask(__name__)

def check_credentials(username, password):
    with open('credentials.csv', mode='r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if row[0] == username and row[1] == password:
                return True
        return False

def add_credentials(username, password):
    with open('credentials.csv', mode='a', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow([username, password])

@app.route('/')
def home():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    if check_credentials(username, password):
        return redirect('/index')  # Redirect to index page on successful login
    else:
        return "Invalid username or password!"

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    if not username or not password:
        return "Username and password cannot be empty!"
    if check_credentials(username, password):
        return "This username is already registered!"
    add_credentials(username, password)
    return "Registration successful!"

@app.route('/index')
def index():
    return render_template('index.html')

if __name__ == '__main__':
    if not os.path.exists('credentials.csv'):
        with open('credentials.csv', 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['username', 'password'])
    app.run(debug=True)
