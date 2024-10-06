def main():
    driver_handle = open('/proc/driver1_proc')
    message_recieved=driver_handle.readline()
    print(message_recieved)
    driver_handle.close()
    return

main()