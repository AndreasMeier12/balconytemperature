from flask import Flask
from flask_migrate import Migrate
from flask_bootstrap import Bootstrap
from config import Config

app = Flask(__name__)



from flask_sqlalchemy import SQLAlchemy
app.config.from_object(Config)
db = SQLAlchemy(app)
Bootstrap(app)
migrate = Migrate(app, db)

from app import models, routes
