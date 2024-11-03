"use client"
import { useState, useEffect } from "react"
export default function Home() {

  const [status, setStatus] = useState("stop");

  const sendReq = (data) => {
    fetch('http://192.168.130.236:8000/', {
      method: 'POST',
      body: JSON.stringify({status:status}),
      headers: {
        "Content-Type": "application/json"
      }
    })
  }

  useEffect(() => {
    sendReq();
  },[status])

  const items = [
    "forward",
    "backward",
    "left",
    "right",
    "stop"
  ]

  return (
    <div className="flex min-h-screen justify-center items-center m-auto container">
      <div className="flex flex-col justify-start items-center gap-2">
        <h3 className="text-2xl text-white">Control me daddy!!!</h3>
        {items.map((item, index) => (
          <button
            className="select-none bg-purple-800 px-4 py-2 rounded-xl text-2xl hover:bg-purple-900"
            key={index}
            onTouchStart={() => setStatus(item)}
            onTouchEnd={() => setStatus("stop")}
          >
            {item}
          </button>
        ))}
      </div>
    </div>
  );
}
