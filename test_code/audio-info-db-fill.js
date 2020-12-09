// A simple script to create and fill a DB with our audio track info, for test purposes
// Only needs to be ran once

var sqlite3 = require('sqlite3').verbose();
var db = new sqlite3.Database('./audio_track_info');

// TODO: Later on we will have to make a "WAV Parser" in C++ to allow users to upload
// For now, just hard-code some values to insert in the DB
var track_name = ["birds.wav", "piano.wav", "space.wav", "wonder.wav"];
var duration = [28, 343, 144, 47];

db.serialize(() => {
	db.run("CREATE TABLE if NOT EXISTS audio_track_info (id INTEGER NOT NULL PRIMARY KEY, \
													    track_name TEXT, \
                                                        duration INT, \
                                                        description TEXT)");

	// Fill the DB with our audio track info
	for(var i = 0; i < track_name.length; i++) {
		db.run(`INSERT INTO audio_track_info (track_name, duration, description) VALUES ('${track_name[i]}', '${duration[i]}', 'test_desc${i}')`);
	}

	console.log("Audio track info DB initialized");
});
 
db.close();