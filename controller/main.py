from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Define a Pydantic model for the request body
class StatusRequest(BaseModel):
    status: str

move = "stop"
active_connections = []

@app.post("/")
async def update_status(request: StatusRequest):
    global move
    print("Received status:", request.status)
    move = request.status

    # Notify all active WebSocket connections
    for connection in active_connections:
        try:
            await connection.send_text(move)
        except Exception as e:
            print(f"Failed to send message: {e}")
    
    return move

@app.get("/")
def noice():
    return move.replace("\"", '')

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    active_connections.append(websocket)
    try:
        while True:
            # Keep the connection alive; receive data if needed (optional)
            data = await websocket.receive_text()
            print(f"Received from WebSocket client: {data}")
    except WebSocketDisconnect:
        active_connections.remove(websocket)
        print("WebSocket client disconnected")

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
