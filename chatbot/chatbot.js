function processInput(){
    const chatArea = document.getElementById("chat");
    const input = document.getElementById("input");

    const userMsg = input.value.trim();

    if(userMsg === ""){
        return ;
    }

    // Create user message box
    const userMsgBox = document.createElement("div");
    userMsgBox.classList.add("message-box", "user-message");
    userMsgBox.textContent = "You: " + userMsg;
    input.value = "";

    // Create bot message box
    const botMsgBox = document.createElement("div");
    botMsgBox.classList.add("message-box", "bot-message");

    setTimeout(()=>{
        chatArea.prepend(userMsgBox); // Append user message to the top

        const text = processText(userMsg);
        botMsgBox.textContent = "Bot: " + text;
        userMsgBox.appendChild(botMsgBox); // Append bot message to the bottom

        // Optionally scroll to the bottom to show the latest messages
        chatArea.scrollTop = chatArea.scrollHeight;
    },1000);

    // Optionally scroll to the bottom after user message
    chatArea.scrollTop = chatArea.scrollHeight;
}

function processText(text){
    let message = text.toLowerCase().replace(/[^\w\s\d]/gi, "");
    message = message
        .replace(/ a /g, " ")
        .replace(/i feel /g, "")
        .replace(/whats/g, "what is")
        .replace(/please /g, "")
        .replace(/ please/g, "");

    const response = compare(trigger, reply, message);
    if (response) {
        return response;
    } else if (message.match(/robot/gi)) {
        return robot[Math.floor(Math.random() * robot.length)];
    } else {
        return alternative[Math.floor(Math.random() * alternative.length)];
    }
}

function compare(triggerArray, replyArray, message) {
    let response = null;
    
    for (let i = 0; i < triggerArray.length; i++) {
        for (let j = 0; j < triggerArray[i].length; j++) {
            // Check if any word from the trigger set is present in the message
            if (message.includes(triggerArray[i][j].toLowerCase())) {
                response = replyArray[i][Math.floor(Math.random() * replyArray[i].length)];
                break; // Exit the loop once a match is found
            }
        }
        
        if (response) {
            break;
        }
    }

    if (!response) {
        response = alternative[Math.floor(Math.random() * alternative.length)];
    }

    return response;
}

const trigger = [
    // Words related to weather
    ["weather", "raining", "sunny", "cloudy", "forecast"],

    // Words related to greetings
    ["hi", "hello", "hey", "howdy", "yo", "greetings", "sup"],

    // Words related to asking about well-being
    ["how", "are", "life", "doing", "been", "feel"],

    // Words related to asking about the bot's identity
    ["bot", "human", "what", "who", "you"],

    // Words related to gratitude
    ["thank", "thanks", "appreciate", "many", "grateful"],

    // Words related to farewells
    ["bye", "goodbye", "later", "take care", "see", "catch"],

    // Words related to jokes
    ["joke", "funny", "laugh", "story", "fun"],

    // Words related to asking for help
    ["help", "assist", "need", "help me", "help me out"]
];

const reply = [
    // Replies related to weather
    ["I'm not sure about the weather right now, but you can check online for updates!", 
     "I don't know the weather at the moment, but you can check a weather website!", 
     "I think it's sunny outside, but I can't be sure."],

    // Replies related to greetings
    ["Hello!", "Hi!", "Hey!", "Howdy!", "Yo!", "Greetings!", "What's up?", "How's it going?", "Hey there!"],

    // Replies related to asking about well-being
    ["I'm doing great, thank you!", "I'm fine, how about you?", "I'm good, thanks for asking!", "Feeling good, how about you?"],

    // Replies related to asking about the bot's identity
    ["I am a bot, an AI designed to help.", "I'm just a friendly chatbot!", "I am an artificial intelligence designed to assist you."],

    // Replies related to gratitude
    ["You're welcome!", "No problem!", "Happy to help!", "Anytime!"],

    // Replies related to farewells
    ["Goodbye, take care!", "See you soon!", "Talk to you later!", "Goodbye, have a great day!"],

    // Replies related to jokes
    ["Why don't you try this one: Why don't skeletons fight each other? They don't have the guts!", 
     "Here's a fun fact: Did you know honey never spoils?", 
     "Here's a joke: Why don't scientists trust atoms? Because they make up everything!"],

    // Replies related to asking for help
    ["Of course! What do you need help with?", "I'm here to assist you. What's the problem?", "What can I do for you?"]
];

const alternative = [
    "Sorry, I don't understand.",
    "Could you please rephrase that?",
    "I'm still learning, can you say that differently?"
];

const robot = ["Beep boop.", "I am a robot.", "I like electricity."];
