// A simple script to create and fill a DB with our audio track info, for test purposes
// Only needs to be ran once

const { Console } = require('console');

var sqlite3 = require('sqlite3').verbose();
var db = new sqlite3.Database('./audio_track_info.db');

// TODO: Later on we will have to make a "WAV Parser" in C++ to allow users to upload
// For now, just hard-code some values to insert in the DB
var track_name = ["birds.wav", "piano.wav", "space.wav", "wonder.wav"];
var duration = [28, 343, 144, 47];

db.serialize(() => {
	db.get("SELECT name FROM sqlite_master WHERE type='table' AND name='track_info'", function(error, row) {

		// Table not found, creating Table
		if (row == undefined) {
			console.log("table DNE. Creating and filling table....");

			// Use a promise so the INSERT statements takes place after DB is created
			const promise = new Promise((resolve, reject) => {
				db.run("CREATE TABLE track_info (id INTEGER NOT NULL PRIMARY KEY, \
												track_name TEXT, \
												duration INT, \
												description TEXT)", (err, rows) => {
													resolve("Done creating table!");
												});
			});
			
			// Fill the DB with our audio track info
			promise.then((result, err) => {
				console.log(result)
				for(var i = 0; i < track_name.length; i++) {
					db.run(`INSERT INTO track_info (track_name, duration, description) VALUES ('${track_name[i]}', '${duration[i]}', 'test_desc${i}')`)
					console.log(i)
				}	
			});

			// Wait for INSERT to finish then close db connection
			promise.then(() => {
				db.close();
			})
													
		} else {
			console.log("Table already created! Doing nothing...");
			db.close();
		}

		
	});
});
 
