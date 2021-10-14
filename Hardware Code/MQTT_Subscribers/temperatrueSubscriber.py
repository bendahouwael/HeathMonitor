import paho.mqtt.client as mqtt
import json
import hashlib
import hmac
import requests
import datetime
import time
MQTT_ADDRESS = '192.168.4.132'
MQTT_USER = 'healthmonitorgateway'
CIN='13017750'
MQTT_PASSWORD = 'healthmonitorgateway'
MQTT_TOPIC = 'patient/' + CIN + '/temperature'

Patienturl= "http://192.168.4.175:8081/api/Patient/"+CIN

PowerBIurl=requests.get(Patienturl).json()['powerBILinkTemp']
print(PowerBIurl)



def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    client.subscribe(MQTT_TOPIC)


def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    #print(msg.topic + ' ' + str(msg.payload.decode('utf8')))
    v=str(msg.payload.decode('utf8'))
    state="normal"
    if (float(v)>=38):
        state="High feaver!"
    #x = datetime.datetime.now()
    x=time.time()
    #'{"user": {"cin": "60b764203aaf00841a4788e5","ipAddress": "192.168.1.1","name": "da7dou7","surName": "dodo"}, "creationDate": "pk,kojk","temperature": "37.7"}'

    print(v)
    #print(x)
    #{ "device" : "TempSensor1", "sample_date" : "2018-09-03", "value" : "72.5", "time" : "1536011844" }
    #body='{ "device" : "TempSensor1", "sample_date" : "2018-09-03", "value" : ' + v + ', "time" : "1536011844" }'
    body= '{"patient": {"cin":"'+ CIN +'" }, "temperature": "' + v +'","gatewayID":"'+ MQTT_USER +'","healthState":"'+ state +'"}'
    print(body)
    body2='{"temperature":'+ v +',"txt":"tempVal","date":'+ str(x) +'}'
    secret = b'mongodbhealthmonitor'
    hash = hmac.new(secret, body2.encode("utf-8"), hashlib.sha256)
    #url = "https://eu-central-1.aws.webhooks.mongodb-realm.com/api/client/v2.0/app/application-0-cuxka/service/healthMonitordata/incoming_webhook/savesensordata"
    url= "http://192.168.4.175:8081/api/Payload"
    url2=PowerBIurl
    #url2="https://api.powerbi.com/beta/8f85f528-6195-4e97-8e41-f5a9ad3bed4a/datasets/0f8dc780-8494-43d7-8085-6276c46621bb/rows?key=WPCRq5zUST857QubOwnrsDnQm8fWNkn4j8WPcWIWdHhMHGi7pUbMcGNa1gg%2FyF%2Bjn3O8jd%2FZfK0WJhbpoVkXOQ%3D%3D&fbclid=IwAR3ZV3sTnd2ET11XQav8HSKD9L-jvCzxgvPpGBbdugjFwOEJOMjG8KSZROA"
    header={"Content-Type":"application/json","X-Hook-Signature":"sha256=" + hash.hexdigest()  }
    #"https://eu-central-1.aws.webhooks.mongodb-realm.com/api/client/v2.0/app/application-0-cuxka/service/healthMonitordata/incoming_webhook/savesensordata"
    myResponse2 = requests.post(url2,headers=header, data=body2 )
    myResponse = requests.post(url,headers=header, data=body )
    print (myResponse.status_code)
    print (myResponse2.status_code)
def main():
    mqtt_client = mqtt.Client()
    mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_ADDRESS, 1883,60)
    mqtt_client.loop_forever()


if __name__ == '__main__':
    print('MQTT to InfluxDB bridge')
    main()
