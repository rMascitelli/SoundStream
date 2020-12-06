// Simple JavaScript example of connecting to AWS S3 bucket, listing contents, and downloading a file
// TODO: It would be cool if I had some auth service to fetch my credentials from a DB somewhere

const { Credentials } = require('aws-sdk');

// Load the AWS SDK for Node.js
var AWS = require('aws-sdk');
var fs = require('fs');

// Set the region 
AWS.config.update({region: 'us-east-2'});


AWS.config.credentials = new AWS.Credentials({
    accessKeyId: '...', secretAccessKey: '...'
});

// Create S3 service object
s3 = new AWS.S3({apiVersion: '2006-03-01'});

// Create the parameters for calling listObjects
var bucketParams = {
    Bucket: 'wav-audio-files',
};

// Call S3 to obtain a list of the objects in the bucket
s3.listObjects(bucketParams, function(err, data) {
  if (err) {
    console.log("Error", err);
  } else {
    console.log("Success", data);
  }
});

// Add "Key" param for getObject()
bucketParams.Key = 'birds.wav'

// We can wrap this section in a nodeJS HTTP response to serve up files to users
s3.getObject(bucketParams, function(err, data) {
    if(err) {
        console.log("error in callback");
        console.log(err)
    }
    console.log("success!");
    console.log(data.Body);

    fs.writeFile('test.wav', data.Body, function (err) {
        if (err) throw err;
        console.log('Saved!');
      });
});

