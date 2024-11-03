import React from 'react'

const Button = () => {
  return (
    <>
        {items.map((item, index) => (
          <button
            className="bg-purple-800 px-4 py-2 rounded-xl text-2xl hover:bg-purple-900"
            key={index}
            //onClick={() => sendReq(item)}
            onKeyDown={() => console.log("Key pressed")} 
            onKeyUp={() => console.log("Key releases")}
          >
            {item}
          </button>
        ))}
    </>
  )
}

export default Button;
