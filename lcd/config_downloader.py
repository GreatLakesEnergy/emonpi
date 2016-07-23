#!/usr/bin/env python
import uuid
import requests

class ConfigDownloader:
    def __init__(self, config_path, remote_url):
        self.config_path = config_path
        self.remote_url  = remote_url
        self.api_key      = uuid.uuid4()

    def run(self):
        print "Setting up a new account"
        print "please make sure an account with API key %s is configured" % self.api_key
        ready = raw_input("press return when ready... ")
        if ready != "":
            print "aborting..."
            exit()
        self.download()
        if self.response.status_code == requests.codes.ok:
            print "writing config file to: " + self.config_path
            self.save()
            print "done."
        else:
            print "dowload failed with status: %s" % self.response.status_code

    def download(self):
        self.response = requests.get(self.remote_url, headers={'X-Api-Key': self.api_key})
        return self.response

    def save(self):
        f = open(self.config_path,"w")
        f.write(self.response.text)
        f.close()


if __name__ == '__main__':
    import os
    config_path = os.environ.get('EMONPI_CONFIG', None)
    remote_url  = os.environ.get('EMONPI_CONFIG_URL', None) or 'https://api.gle.solar/config'
    if config_path == None or remote_url == None:
        print "aborting. please provide a EMONPI_CONFIG path and an EMONPI_CONFIG_URL URL"
        print "EMONPI_CONFIG: %s - EMONPI_CONFIG_URL: %s" % (config_path, remote_url)
        exit()

    ConfigDownloader(config_path, remote_url).run()

