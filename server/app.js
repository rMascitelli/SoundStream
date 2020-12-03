// Get Dependencies
const express = require('express');
const app = express();
const cors = require('cors');

// Setup CORS
app.use(cors())
console.log("Starting server from server.js");

// EXPRESS ROUTES

app.get('/', (req, res) => {
	res.send('Hello World: root folder');
    console.log('Got a request at /root');
});


var port = 8080;
app.listen(port, () => console.log(`Listening on Port ${port}...`));