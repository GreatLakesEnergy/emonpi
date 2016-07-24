#!/usr/bin/env python
import uuid
import requests
import codecs

class ConfigDownloader:
    def __init__(self, config_path, remote_url):
        self.config_path = config_path
        self.remote_url  = remote_url
        self.api_key     = uuid.uuid4()
        self.error       = None
        self.response    = None

    def run(self):
        print "Setting up a new account"
        print "please make sure an account with API key %s is configured" % self.api_key
        ready = raw_input("press return when ready... ")
        if ready != "":
            print "aborting..."
            exit()
        if self.download():
            print "writing config file to: " + self.config_path
            if self.save():
                print "done."
            else:
                print "error writing file:"
                print self.error
        else:
            print "dowload failed:"
            print self.response
            print self.error

    def download(self):
        try:
          self.response = requests.get(self.remote_url, headers={'X-Api-Key': self.api_key})
          return self.response.status_code == requests.codes.ok
        except Exception as e:
          self.error = e
          return False

    def save(self):
        try:
            f = codecs.open(self.config_path, "w", encoding='utf8')
            f.write(self.response.text)
            f.close()
            return True
        except Exception as e:
            self.error = e
            return False


if __name__ == '__main__':
    import os
    config_path = os.environ.get('EMONPI_CONFIG', None)
    remote_url  = os.environ.get('EMONPI_CONFIG_URL', None) or 'https://api.gle.solar/config'
    if config_path == None or remote_url == None:
        print "aborting. please provide a EMONPI_CONFIG path and an EMONPI_CONFIG_URL URL"
        print "EMONPI_CONFIG: %s - EMONPI_CONFIG_URL: %s" % (config_path, remote_url)
        exit()

    ConfigDownloader(config_path, remote_url).run()

