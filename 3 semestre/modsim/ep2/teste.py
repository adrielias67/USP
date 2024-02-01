from kivy.app import App
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.screenmanager import ScreenManager, Screen, NoTransition
from kivy.uix.label import Label
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import StringProperty
from kivy.clock import Clock
from kivy_garden.graph import Graph, LinePlot

import numpy as np
from plyer import accelerometer
from scipy.signal import find_peaks


# Cira o screen manager
sm = ScreenManager(transition=NoTransition())


# Define as screens
class HomeScreen(Screen):
    pass


class AcelerometroScreen(Screen):
    pass


class FindPeaksScreen(Screen):
    def build(self):
        start_gap = StringProperty("")
        end_gap = StringProperty("")
        distance = StringProperty("")
        prominence = StringProperty("")

    # Acha os picos
    def find_peaks_function(self):
        start_gap = float(self.start_gap)
        end_gap = float(self.end_gap)
        distance = float(self.distance)
        prominence = float(self.prominence)
        #peaks, _ = find_peaks(grafico, distance=distance, prominence=prominence)
        print(start_gap, end_gap, distance, prominence)
    
    pass


class EulerScreen(Screen):
    pass


# Carrega o builder com o arquivo .kv de formatação
Builder.load_file('teste.kv')

# Adiciona as screens no screen manager
sm.add_widget(HomeScreen(name='home'))
sm.add_widget(AcelerometroScreen(name='acelerometro'))
sm.add_widget(FindPeaksScreen(name='find_peaks'))
sm.add_widget(EulerScreen(name='euler'))


# Aplicativo
class MyApp(App):
    def build(self):
        return sm

    def start_accelerometer(self, instance):
        accelerometer.enable()
        Clock.schedule_interval(self.update_accelerometer, 1.0/60.0)

    def stop_accelerometer(self):
        accelerometer.disable()

    def update_accelerometer(self, dt):
        acceleration = accelerometer.acceleration
        self.label.text = f"X: {acceleration[0]}, Y: {acceleration[1]}, Z: {acceleration[2]}"


if __name__ == '__main__':
    MyApp().run()