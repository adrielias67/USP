from kivy.app import App
from kivy.uix.widget import Widget
from kivy.garden.graph import Graph, LinePlot
from kivy.clock import Clock
from kivy.uix.screenmanager import ScreenManager, Screen

# Seta o design em "ep2.kv"
from kivy.lang import Builder
Builder.load_file("ep2.kv")


# Diferentes abas do aplicativo
class Acelerometro(Screen):
    pass

class FindPeaks(Screen):
    pass

class WindowManager(ScreenManager):
    pass



class aplicativo(Widget):
    # Código do aplicativo
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        


class mainApp(App):
    def build(self):
        return aplicativo()


if __name__ == '__main__':
    app().run()