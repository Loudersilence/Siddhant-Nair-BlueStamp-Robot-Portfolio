import cv2
import serial
import time

# Initialize serial communication with the Arduino
ser = serial.Serial('/dev/ttyUSB0', 115200)  # Replace '/dev/ttyUSB0' with the appropriate serial port


def send_command(command):
    ser.write((command + '\n').encode())
    print(f'Sent: {command}')
    time.sleep(0.1)


classNames = []
classFile = "/home/nairs/Desktop/Object_Detection_Files/coco.names"
with open(classFile, "rt") as f:
    classNames = f.read().rstrip("\n").split("\n")

configPath = "/home/nairs/Desktop/Object_Detection_Files/ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt"
weightsPath = "/home/nairs/Desktop/Object_Detection_Files/frozen_inference_graph.pb"

net = cv2.dnn_DetectionModel(weightsPath, configPath)
net.setInputSize(180, 180)
net.setInputScale(1.0 / 127.5)
net.setInputMean((127.5, 127.5, 127.5))
net.setInputSwapRB(True)


def getObjects(img, thres, nms, draw=True, objects=[]):
    classIds, confs, bbox = net.detect(img, confThreshold=thres, nmsThreshold=nms)
    if len(objects) == 0:
        objects = classNames
    objectInfo = []
    if len(classIds) != 0:
        for classId, confidence, box in zip(classIds.flatten(), confs.flatten(), bbox):
            className = classNames[classId - 1]
            if className in objects:
                objectInfo.append([box, className])
                if draw:
                    cv2.rectangle(img, box, color=(0, 255, 0), thickness=2)
                    cv2.putText(img, classNames[classId - 1].upper(), (box[0] + 10, box[1] + 30),
                                cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 2)
                    cv2.putText(img, str(round(confidence * 100, 2)), (box[0] + 200, box[1] + 30),
                                cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 2)
    return img, objectInfo


def execute_commands():
    # First set of commands
    send_command("UP:170")  # Command to move the arm right
    send_command("DOWN:20")  # Command to move the arm down
    time.sleep(2)

    send_command("CLOSE:5")
    time.sleep(2)  # Wait for 2 seconds for the arm to complete the first set of commands

    # Second set of commands
    send_command("CLOSE:5")
    send_command("DOWN:90")  # Command to move the arm up
    send_command("UP:90")
    send_command("RIGHT:180")

    time.sleep(2)  # Wait for 2 seconds for the arm to complete the second set of commands

    send_command("CLOSE:5")
    send_command("DOWN:20")
    send_command("UP:165")
    time.sleep(2)

    send_command("OPEN:90")


if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    cap.set(3, 640)
    cap.set(4, 480)

    commands_executed = False  # Flag to check if commands have been executed

    while True:
        success, img = cap.read()
        result, objectInfo = getObjects(img, 0.60, 0.2, objects=['person'])

        if not commands_executed and objectInfo:
            execute_commands()  # Execute the sets of commands sequentially
            commands_executed = True  # Set flag to true after executing commands

        cv2.imshow("Output", img)
        if cv2.waitKey(1) & 0xFF == ord('q') or commands_executed:
            break

    cap.release()
    cv2.destroyAllWindows()
    ser.close()
