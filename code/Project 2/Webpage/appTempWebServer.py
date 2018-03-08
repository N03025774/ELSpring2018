from flask import Flask, render_template, request
app = Flask(__name__)
import sqlite3
# Retrieve data from database

def getData():
	con=sqlite3.connect('/home/dave/ELSpring2018/code/Project 2/Python/temperature.db')
	cur=con.cursor()
	for row in cur.execute("SELECT * FROM TempData ORDER BY timestamp DESC LIMIT 1"):
		time = str(row[0])
		tempC = row[1]
		tempF = row[2]
	conn.close()
	return time, tempC, tempF

# main route
@app.route("/")
def index():
	time, tempC, tempF = getData()
	templateData = {
		'time': time,
		'tempC': tempC,
		'tempF': tempF
	}
	return render_template('index.html', **templateData)

if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80, debug=False)
