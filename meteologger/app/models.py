from datetime import datetime

from sqlalchemy import DateTime, INTEGER, Float

from app import db
class Measurement(db.Model):
    id = db.Column(INTEGER, primary_key=True, autoincrement=True)
    timestamp = db.Column(DateTime, default=datetime.utcnow, nullable=False)
    temperature = db.Column(Float, nullable=False)
    humidity = db.Column(Float, nullable=False)

    def __init__(self, temp_value: float, humidity_value: float):
        self.timestamp = datetime.now()
        self.temperature = temp_value
        self.humidity = humidity_value
