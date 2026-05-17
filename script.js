function sendMessage()
{
    let userinput = document.getElementById("userInput");
    let chatbox = document.getElementById("chat");

    let usertext = userinput.value.trim();
    if(usertext === "") return;

    let userMessage = document.createElement("div");
    userMessage.innerHTML = "You:" + usertext;
    userMessage.className = "user-message";
    chatbox.appendChild(userMessage);

    let botReply = messageResponse(usertext);

    let botMessage = document.createElement("div");
    botMessage.innerHTML = "Bot:" + botReply;
    botMessage.className = "bot-message";
    chatbox.appendChild(botMessage);

    userinput.value = "";
}

function messageResponse(userText)
{
    userText = userText.toLowerCase();

    if(userText.includes("hello") || userText.includes("hi"))
    {
        return "Hello, how can I help you today?";
    }
    else if(userText.includes("day") || userText.includes("open"))
    {
        return "We are open all 7 days a week!"
    }
    else if(userText.includes("time"))
    {
        return "Our courts are available from 6AM to 10PM"
    }
    else if(userText.includes("book"))
    {
        return "To book a court, try calling our reception\nMobile Number: +91 9846378382"
    }
    else if(userText.includes("court"))
    {
        return "We own 5 courts in our facility!"
    }
    else if(userText.includes("park"))
    {
        return "Yes we have parking facility!"
    }
    else if(userText.includes("contact") || userText.includes("mobile") || userText.includes("phone"))
    {
        return "Contact Number: 87383493843"
    }
    else
    {
        return "Sorry! I couldn't understand!";
    }
}

document.getElementById("userInput").addEventListener("keydown", function(event)
{
    if(event.key === "Enter")
    {
        event.preventDefault();
        sendMessage();
    }
});