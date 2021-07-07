    char byte_recebido;
    int packet_size = 0;
    int lora_rssi = 0;
    long informacao_recebida = 0;
    char * ptInformaraoRecebida = NULL;
    String resul;
   
    /* Verifica se chegou alguma informação do tamanho esperado */
    packet_size = LoRa.parsePacket();
    Serial.println(packet_size);
     
    //if (packet_size == sizeof(informacao_recebida)) {
    if (packet_size) {
        Serial.print("[LoRa Receiver] Há dados a serem lidos");
         
        /* Recebe os dados conforme protocolo */               
        ptInformaraoRecebida = (char *)&informacao_recebida;  
        while (LoRa.available()) {
            byte_recebido = (char)LoRa.read();
            *ptInformaraoRecebida = byte_recebido;
            ptInformaraoRecebida++;
            resul += ptInformaraoRecebida;
        }
 
        /* Escreve RSSI de recepção e informação recebida */
        lora_rssi = LoRa.packetRssi();
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("RSSI: ");
        display.println(lora_rssi);
        display.setCursor(0, OLED_LINE2);
        display.print("Informacao: ");
        display.setCursor(0, OLED_LINE3);
        display.println(resul);
        display.display();      
    }