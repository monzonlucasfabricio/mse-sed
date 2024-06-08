import csv
import paho.mqtt.client as mqtt
import matplotlib.pyplot as plt

# Archivo CSV donde se guardarán los datos
csv_file = 'ldr.csv'

# Callback cuando nos conectamos al broker MQTT
def on_connect(client, userdata, flags, rc):
    print(f"Conectado con el código {rc}")
    # Nos suscribimos al tópico
    client.subscribe("p2/csv_value")

# Callback cuando recibimos un mensaje del broker MQTT
def on_message(client, userdata, msg):
    # Convertimos el payload a string y procesamos los valores de tiempo y valor
    payload = msg.payload.decode()
    print(f"Mensaje recibido: {payload}")
    try:
        tiempo, valor = map(int, payload.split(","))
        save_to_csv(tiempo, valor)
    except ValueError:
        print(f"Error al procesar el mensaje: {payload}")

def save_to_csv(tiempo, valor):
    with open(csv_file, 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([tiempo, valor])
    print(f"Valor guardado en {csv_file}")

def plot_values():
    tiempos = []
    valores = []
    with open(csv_file, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if row:  # Verifica que la fila no esté vacía
                tiempos.append(int(row[0]))
                valores.append(int(row[1]))

    plt.plot(tiempos, valores)
    plt.xlabel('Tiempo')
    plt.ylabel('Valor')
    plt.title('Valores del sensor LDR')
    plt.grid(True)
    plt.show()

# Configuración del cliente MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Conexión al broker MQTT
broker_ip = "192.168.0.87"
client.connect(broker_ip, 1883, 60)

# Iniciamos el loop para manejar los callbacks
client.loop_start()

# Mantener el script en ejecución
try:
    while True:
        pass
except KeyboardInterrupt:
    print("Desconectando del broker MQTT...")
    client.loop_stop()
    client.disconnect()
    plot_values()