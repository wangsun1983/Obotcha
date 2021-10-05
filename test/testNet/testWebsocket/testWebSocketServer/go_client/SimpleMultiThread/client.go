package main

import (
    "fmt"
    "../../../../../3rdparty/go/net/websocket"
    "log"
    "sync"
)

var wg sync.WaitGroup

func doSend(id int) {
  origin := "http://localhost/"
  url := "ws://localhost:1111/mytest"
  fmt.Println("start: " ,id)
  for i:= 0;i<80;i++ {
      ws, err := websocket.Dial(url, "", origin)
      if err != nil {
          log.Fatal(err)
      }
      
      if _, err := ws.Write([]byte("Hello, World")); err != nil {
          log.Fatal(err)
      }
      ws.Close()
  }
  wg.Done()
  fmt.Println("finish :", id)
}

func main() {
  wg.Add(128)
  for i:= 0;i<128;i++ {
    go doSend(i)
  }
  wg.Wait()

}
