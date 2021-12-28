from http.server import BaseHTTPRequestHandler, HTTPServer
import socket
import xml.etree.ElementTree as ET
import copy

data_to_parse = 'data.xml'

result = {'number': int()}
list_of_result = list()

xml_tree = ET.parse(data_to_parse)

root = xml_tree.getroot()

for elem in root.findall('player'):
    number = elem.attrib['number']
    result['number'] = number
    list_of_result.append(copy.deepcopy(result))

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
hostName = str(s.getsockname()[0])
serverPort = 8080

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.endswith('/number'):
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            for el in list_of_result:
                self.wfile.write(bytes("{};".format(el['number']), "utf-8"))


if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")
