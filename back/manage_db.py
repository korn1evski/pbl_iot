import sqlite3
import sys

DB = "attendance.db"

def add_student(uid, name, group):
    with sqlite3.connect(DB) as conn:
        cur = conn.cursor()
        cur.execute("INSERT OR IGNORE INTO students (uid, name, student_group) VALUES (?, ?, ?)", (uid, name, group))
        conn.commit()
        print(f"✅ Student added: {name} ({uid}) - {group}")

def add_schedule(classroom, day, start_time, end_time, group, subject):
    with sqlite3.connect(DB) as conn:
        cur = conn.cursor()
        cur.execute("INSERT INTO schedule (classroom, day, start_time, end_time, student_group, subject) VALUES (?, ?, ?, ?, ?, ?)",
                    (classroom, day, start_time, end_time, group, subject))
        conn.commit()
        print(f"✅ Schedule added: {subject} for {group} in {classroom} on {day} from {start_time} to {end_time}")

def list_students():
    with sqlite3.connect(DB) as conn:
        cur = conn.cursor()
        cur.execute("SELECT * FROM students")
        for row in cur.fetchall():
            print(row)

def list_schedule():
    with sqlite3.connect(DB) as conn:
        cur = conn.cursor()
        cur.execute("SELECT * FROM schedule")
        for row in cur.fetchall():
            print(row)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:")
        print("  python manage_db.py add_student UID Name Group")
        print("  python manage_db.py add_schedule Room Day Start End Group Subject")
        print("  python manage_db.py list_students")
        print("  python manage_db.py list_schedule")
        sys.exit(1)

    command = sys.argv[1]

    if command == "add_student" and len(sys.argv) == 5:
        add_student(sys.argv[2], sys.argv[3], sys.argv[4])

    elif command == "add_schedule" and len(sys.argv) == 8:
        add_schedule(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])

    elif command == "list_students":
        list_students()

    elif command == "list_schedule":
        list_schedule()

    else:
        print("❌ Invalid command or missing arguments.")
