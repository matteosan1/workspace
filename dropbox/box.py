import traceback
from boxsdk import JWTAuth, Client

from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot, QThread

class UpdateThread(QThread):
    startThread = pyqtSignal()
    endThread = pyqtSignal()

    def __init__(self, client, music_folder):
        super(UpdateThread, self).__init__()
        self.client = client
        self.music_folder = music_folder
        self.filepath = None
        self.new_filename = None

    def run(self):
        self.startThread.emit()
        try:
            new_file = self.music_folder.upload(self.filepath, file_name=None, file_description=None)
            self.new_filename = new_file.name
        except Exception as e:
            file_id = e.context_info['conflicts']['id']
            updated_file = self.client.file(file_id).update_contents(self.filepath)
            self.new_filename = updated_file.name
        self.endThread.emit()

class BoxHelper:
    def __init__(self):
        config = JWTAuth.from_settings_file('800515977_eqwyjy8m_config.json')
        self.client = Client(config)
        self.user_to_impersonate = self.client.user(user_id='226100449')
        self.user_client = self.client.as_user(self.user_to_impersonate)
        self.music_folder = self.user_client.root_folder().get()
        self.update_thread = UpdateThread(self.user_client, self.music_folder)

    
    def getFullList(self):
        items = self.music_folder.get_items()
        with open("lista.csv", 'w') as f:
            for item in items:
                if item.type == "file":
                    f.write(item.name+";"+item.id+"\n")
                    #print('{0} {1} is named "{2}"'.format(item.type.capitalize(), item.id, item.name))
        

    def upload(self, filepath):
        self.update_thread.filepath = filepath
        self.update_thread.start()

    def remove(self, file_id):
        self.user_client.file(file_id=file_id).delete()

    def getEvents(self):
         events = self.user_client.events().get_admin_events(created_after='2021-03-01T22:02:24+01:00')
         for event in events['entries']:
             print('Got {0} event that occurred at {1}'.format(event.event_type, event.created_at)) 

    def getMostRecent(self, limit=10):
        items = self.music_folder.get_items(limit=limit, sort='date', direction='DESC', fields=["modified_at", "name"])
        for i, item in enumerate(items):
            if item.type == 'folder':
                continue
            if i > 2:
                break
            print (dir(item.metadata()))
            print('{0} {1} is named "{2}"'.format(item.type.capitalize(), item.modified_at, item.name))

    def url(self, file_id):
        return self.user_client.file(file_id).get_download_url()
    
             
#print (user_client.user().get())
##users = client.users(user_type='all')
##for user in users:
##    print('{0} (User ID: {1})'.format(user.name, user.id))
##collections = client.collections()
##print (collections)
##for collection in collections:
##    print('Collection "{0}" has ID {1}'.format(collection.name, collection.id))
#
##enterprise = client.get_current_enterprise()
##invitation = enterprise.invite_user('matteosan1@gmail.com')
#



#
##

