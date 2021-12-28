import mysql.connector
import xml.etree.ElementTree as ET
import copy

mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  password="55555",
  database="gameresult"
)

mycursor = mydb.cursor()

data_to_parse = 'data.xml'

result = {'number': int()}
list_of_result = list()

xml_tree = ET.parse(data_to_parse)

root = xml_tree.getroot()

session_time = root.find('session_time').text

for elem in root.findall('player'):
    number = elem.attrib['number']
    result['number'] = number
    list_of_result.append(copy.deepcopy(result))

create_table = winner (
	session_id datetime,
	number int, 
);

mycursor.execute(create_table)

for el in list_of_ship_values:
    insert = "INSERT INTO winner (session_id, number) VALUES (%s, %s)"
    val = (session_time, el['number'])
    mycursor.execute(insert, val)
    
mydb.commit()

print(len(list_of_result), "records inserted.")

print(mydb)
