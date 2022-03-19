import base64
import datetime
from io import BytesIO

from flask import render_template, jsonify, request, abort
from app import db, app
from app.models import Measurement

from matplotlib.figure import Figure

@app.route('/index')
@app.route('/')
def index():
    return render_template('index.html')


@app.route('/temperatures')
def show_temperature():
    temperatures = Measurement.query.filter(
        Measurement.timestamp > datetime.datetime.now() - datetime.timedelta(
            days=1)).all()
    temp_timestamp = [x.temperature for x in temperatures]
    temp_values = [x.timestamp for x in temperatures]
    fig = Figure()
    ax = fig.subplots()
    ax.plot(temp_timestamp, temp_values)
    buf = BytesIO()
    fig.savefig(buf, format="png")
    img = base64.b64encode(buf.getbuffer()).decode("ascii")
    return render_template('temperatures.html',
                           temperature_values=temperatures, img=img)


@app.route('/api/measurement', methods=['GET', 'POST'])
def post_measurement():
    provided_passphrase: str = request.args.get('passphrase')
    if app.config['PASSPHRASE'] != provided_passphrase:
        abort(401)
    temperature: float = float(request.args.get('temperature'))
    humidity: float = float(request.args.get('humidity'))
    val = Measurement(temperature, humidity)
    db.session.add(val)
    db.session.commit()

    return jsonify(success=True)
