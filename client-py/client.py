# First attempt at using Python requests for HTTP requests
import requests
import os

# Fetch song names from DB, and print them out
r = requests.get('http://localhost:8080/list')
test_dict = r.json()                # r.json() returns a list of dicts

print("Track list: \n")
i = 0
for dic in r.json():
    key = str(list(dic)[0])         # Get key value to access dictionary value
    print(str(i), ": ", dic[key])
    i += 1

# Select a song, and form the JSON object for HTTP request
index = int(input("Which song would you like?: "))
while(index > len(test_dict)-1):
    index = int(input("Song choice OOB, please try again: "))
    
track_name = list(r.json()[index].values())[0]
print("DEBUG: Chose song - ", track_name)

json_data = {'track_name':track_name}
wav_file = requests.post('http://localhost:8080/list', json = json_data)
t = wav_file
      
# Write the response body to a WAV file and play it
try:
    f = open("test.wav", "xb")
except:
    os.remove("test.wav")
    f = open("test.wav", "wb")
    
f.write(wav_file.content)
f.close()

print("Finished!")
