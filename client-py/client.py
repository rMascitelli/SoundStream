# First attempt at using Python requests for HTTP requests
import requests

# Fetch song names from DB, and print them out
r = requests.get('http://localhost:8080/list')

print("Track list: \n")
i = 0

# r.json() returns a list of dicts
test_dict = r.json()
for dic in r.json():
    key = str(list(dic)[0])         # Get key value to access dictionary value
    print(str(i), ": ", dic[key])
    i += 1

# Select a song, and form the JSON object for HTTP request
index = int(input("Which song would you like?: "))
track_name = list(r.json()[index].values())[0]
print("DEBUG: Chose song - ", track_name)

# TODO: My POST request body seems empty when I receive it with Node
wav_file = requests.post('http://localhost:8080/list', data = {'track_name':'birds.wav'})
print(wav_file)
