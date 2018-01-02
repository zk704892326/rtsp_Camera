#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, os.path, time
import threading
import sqlite3
import traceback
import datetime
import json

def create_configs(dbpath):
    db = sqlite3.connect(dbpath)
    sql = '''
        DROP TABLE IF EXISTS configs;
        CREATE TABLE configs (
            name TEXT UNIQUE NOT NULL,
            data TEXT UNIQUE
        );
    '''
    c = db.cursor()
    c.executescript(sql)
    
    sql = "INSERT INTO configs (name, data) VALUES (?, ?)"
    data = {
               'video1': {
                   'url': 'rtsp://192.168.1.103:554/snl/live/1/1',
                   'enable': True
               },
               'video2': {
                   'url': 'rtsp://192.168.1.102:554/snl/live/1/1',
                   'enable': True
               },
               'motor1': {
                   'ip': '192.168.1.102',
                   'port': 30001
               },
               'motor2': {
                   'ip': '192.168.1.107',
                   'port': 8000
               },
               'cruise': False
           }
    values = ('settings', json.dumps(data))
    c.execute(sql, values)
    db.commit()
    db.close()


def create_tasks(dbpath):
    db = sqlite3.connect(dbpath)
    sql = '''
        DROP TABLE IF EXISTS tasks;
        CREATE TABLE tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            time TEXT UNIQUE NOT NULL,
            enable TEXT NOT NULL
        );
    '''
    c = db.cursor()
    c.executescript(sql)
    
    time0 = datetime.datetime.now()
    time0 = time0 + datetime.timedelta(minutes=3)
    sql = "INSERT INTO tasks (time, enable) VALUES (?, ?)"
    time_step = 30
    time_range = 24 * 60 / time_step
    for i in range(time_range):
        timestr = time0.strftime('%H:%M')
        values = (timestr, 'true')
        c.execute(sql, values)
        time0 = time0 + datetime.timedelta(minutes=time_step)
    db.commit()
    db.close()

def create_points(dbpath):
    db = sqlite3.connect(dbpath)
    sql = '''
        DROP TABLE IF EXISTS points;
        CREATE TABLE points (
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            name INTEGER UNIQUE NOT NULL,
            motor TEXT NOT NULL,
            img_path TEXT NOT NULL,
            img_area TEXT NOT NULL,
            key_point TEXT NOT NULL
        );
    '''
    c = db.cursor()
    c.executescript(sql)
    
    #sql = "INSERT INTO points (name, motor, img_path, img_area, key_point) VALUES (?, ?, ?, ?, ?)"
    #motor = [0, 0, 0, 0, 0, 0]
    #for i in range(3):
    #    motorstr = ','.join([str(x) for x in motor])
    #    motor = [x+10 for x in motor]
    #    values = (str(i+1), motorstr, '', '', 'true')
    #    c.execute(sql, values)
    db.commit()
    db.close()

def create_records(dbpath):
    db = sqlite3.connect(dbpath)
    sql = '''
        DROP TABLE IF EXISTS records;
        CREATE TABLE records (
            id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            time TEXT NOT NULL,
            point TEXT NOT NULL,
            state TEXT NOT NULL,
            img_path TEXT NOT NULL
        );
    '''
    c = db.cursor()
    c.executescript(sql)
    
    #time0 = datetime.datetime.now()
    #sql = "INSERT INTO records (time, point, state) VALUES (?, ?, ?)"
    #for i in range(60):
    #    time0 = time0 + datetime.timedelta(minutes=20)
    #    timestr = time0.strftime('%H:%M')
    #    values = (timestr, '1', 'ok')
    #    c.execute(sql, values)
    db.commit()
    db.close()

if __name__ == '__main__':
    create_tasks('camera.db')
    create_points('camera.db')
    create_records('camera.db')
    create_configs('camera.db')

