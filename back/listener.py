# listener.py
import sqlite3
import serial

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
    if not schedule:
        return "No class to enroll"

    expected_group = schedule[0]
    if student_group == expected_group:
        return f"Welcome, {name}"
    else:
        return f"You are not from {expected_group}"

def main():
    ser = serial.Serial('/dev/tty.usbserial-0001', 115200)  # Replace with your ESP32 COM port

    while True:
        if ser.in_waiting:
            data = ser.readline().decode().strip()
            print(f"Received: {data}")
            parts = data.split(',')

            if len(parts) == 4:
                uid, room, time_now, day = parts
                message = check_attendance(uid, room, time_now, day)
                print("Sending:", message)
                ser.write((message + "\n").encode())

if __name__ == "__main__":
    main()
