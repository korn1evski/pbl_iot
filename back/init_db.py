# init_db.py
import sqlite3

conn = sqlite3.connect("attendance.db")
cur = conn.cursor()

# Table for students
cur.execute("""
CREATE TABLE IF NOT EXISTS students (
    uid TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    student_group TEXT NOT NULL
);
""")

# Table for schedule
cur.execute("""
CREATE TABLE IF NOT EXISTS schedule (
    classroom TEXT,
    day TEXT,
    start_time TEXT,
    end_time TEXT,
    student_group TEXT,
    subject TEXT
);
""")

# Sample data
cur.execute("INSERT OR IGNORE INTO students VALUES (?, ?, ?)", ("A1B2C3D4", "Bogdan", "FAF-222"))
cur.execute("INSERT OR IGNORE INTO students VALUES (?, ?, ?)", ("A5B6C7D8", "Maria", "FAF-111"))

cur.execute("INSERT INTO schedule VALUES (?, ?, ?, ?, ?, ?)",
    ("Room101", "Monday", "12:00", "13:00", "FAF-222", "Math"))
cur.execute("INSERT INTO schedule VALUES (?, ?, ?, ?, ?, ?)",
    ("Room101", "Monday", "13:00", "14:00", "FAF-111", "Physics"))

conn.commit()
conn.close()
print("Database initialized.")