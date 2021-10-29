import websockets
import asyncio

class WSserver():
    async def handle(self,websocket,path):
      recv_msg = await websocket.recv()
      print("i received %s" %recv_msg)
      await websocket.send('server send ok')

    def run(self):
      ser = websockets.serve(self.handle,"192.168.1.10","1111")
      asyncio.get_event_loop().run_until_complete(ser)
      asyncio.get_event_loop().run_forever()

ws = WSserver()
ws.run()
