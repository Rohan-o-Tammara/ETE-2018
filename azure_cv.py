import requests

import matplotlib.pyplot as plt
from PIL import Image
from io import BytesIO

subscription_key = "01c8333210854059a6c2df093bf1b284"
assert subscription_key

vision_base_url = "https://westcentralus.api.cognitive.microsoft.com/vision/v2.0/"

analyze_url = vision_base_url + "analyze"
image_path = "D:/name.jpg"
image_data = open(image_path, "rb").read()
headers    = {'Ocp-Apim-Subscription-Key': subscription_key,
              'Content-Type': 'application/octet-stream'}
params     = {'visualFeatures': 'Categories,Description,Color'}
response = requests.post(
    analyze_url, headers=headers, params=params, data=image_data)
response.raise_for_status()
print(type(str(response)),str(response))

# The 'analysis' object contains various fields that describe the image. The most
# relevant caption for the image is obtained from the 'description' property.
analysis = response.json()
print('analysis',analysis)
try:
    image_caption = analysis["description"]["captions"][0]["text"].capitalize()
except:
    print('no caption found')
    image_caption = 'No image caption'
# Display the image and overlay it with the caption.
