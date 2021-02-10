import json
import random
 
 
def lambda_handler(event, context):
    request = event['Records'][0]['cf']['request']
    headers = request['headers']
    
    experimentUri = request['uri']
    experimentUri = experimentUri . '?' . 'keyword=value'
    request['uri'] = experimentUri
    
    return request
    