from abc import abstractmethod, ABC

class ISubscriber(ABC):
    @abstractmethod
    def notify(self, video):
        pass

class Video:
    def __init__(self, name):
        self.name = name

class User(ISubscriber):
    def __init__(self, user_name):
        self.user_name = user_name

    def notify(self, video):
        print("Я, " + self.user_name + ", получил уведомление о новом видео, начинаю смотреть")
        self.show(video)

    def show(self, video):
        print("Смотрю видео " + video.name + "\n")

class Channel:
    def __init__(self):
        self.subscribers = []

    def subscribe(self, subscriber):
        if isinstance(subscriber, ISubscriber):
            self.subscribers.append(subscriber)

    def unsubscribe(self, subscriber):
        self.subscribers.remove(subscriber)

    def addNewVideo(self, video):
        print("Добавлено видео " + video.name)
        for i in self.subscribers:
            i.notify(video)

def main():
    user1 = User("Вася")
    publisher = Channel()
    publisher.subscribe(user1)
    publisher.subscribe(User("Костя"))
    publisher.addNewVideo(Video("Прыжки на мотоциклах"))

    publisher.unsubscribe(user1)
    publisher.addNewVideo(Video("Котики"))

if __name__ == "__main__":
    main()