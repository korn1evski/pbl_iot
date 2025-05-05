from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def check_attendance(uid, room, time_now, day):
    conn = sqlite3.connect("attendance.db")
    cur = conn.cursor()

    cur.execute("SELECT name, student_group FROM students WHERE uid = ?", (uid,))
    student = cur.fetchone()

    if not student:
        return "Unknown card"

    name, student_group = student

    cur.execute("""
        SELECT student_group FROM schedule 
        WHERE classroom = ? AND day = ? 
        AND start_time <= ? AND end_time > ?
    """, (room, day, time_now, time_now))

    schedule = cur.fetchone()
    conn.close()

    if not schedule:
        return "No class to enroll"

    expected_group = schedule[0]
    if student_group == expected_group:
        return f"Welcome, {name}"
    else:
        return f"You are not from {expected_group}"

@app.route('/check', methods=['POST'])
def check():
    data = request.get_json()
    uid = data.get("uid")
    room = data.get("room")
    time_now = data.get("time")
    day = data.get("day")

    result = check_attendance(uid, room, time_now, day)
    return jsonify({"response": result})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001)
