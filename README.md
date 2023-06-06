# Pantry-io communication

Pantry-io linux communication program, handles communication with devices and cloud.

## Compiling
The project is built using CMake and requires glib and mosquitto development libraries.

## Basics
The pantry-io communicator subscribes to pantry-io/+/+ MQTT messages and handles events from devices connected to the MQTT network.
The sensor IoT devices connected to the pantry-io MQTT should publish data about the storage, like the storage conditions and most improtantly which of the item holder places are in stock and which are not.
The sensor devices should only publish info of the indexes that they have in stock. The pantry-io communicator stores the information linking the device ID and it's index to the item name.

The communicator also handles sending the data to a cloud and provides a DBus interface for UI programs to fetch info of the items stored.

Another task of the communicator is the joining of sensor devices.
It should be able to detect nearby devices in joining mode by bluetooth, and send the network credentials to these devices.

## Data format
The IoT devices should publish the item data under the MQTT topic pantry-io/[device-id]/items.
The format of the item data is `"index_of_item=state,index_of_item=state,..."`.

