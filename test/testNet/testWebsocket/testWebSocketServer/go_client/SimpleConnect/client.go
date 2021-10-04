package main

import (
    //"fmt"
    "../../../../../3rdparty/go/net/websocket"
    "log"
)

func main() {
    origin := "http://localhost/"
    url := "ws://localhost:1114/mytest"
    ws, err := websocket.Dial(url, "", origin)
    if err != nil {
        log.Fatal(err)
    }
    
    if _, err := ws.Write([]byte("Hello, World")); err != nil {
        log.Fatal(err)
    }
    
    //var msg = make([]byte, 512)
    //var n int
    //if n, err = ws.Read(msg); err != nil {
    //    log.Fatal(err)
    //}
    //fmt.Printf("Received: %s.\n", msg[:n])
}
