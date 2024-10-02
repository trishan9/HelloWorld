import 'dart:convert';
import 'dart:ui';
import 'package:flutter/material.dart';
import 'package:flutter_spinkit/flutter_spinkit.dart';
import 'package:intl/intl.dart';
import 'package:weather_app/additional_info_item.dart';
import 'package:weather_app/hourly_forecast_item.dart';
import 'package:http/http.dart' as http;
import 'package:weather_app/secrets.dart';

class WeatherScreen extends StatefulWidget {
  const WeatherScreen({super.key});

  @override
  State<WeatherScreen> createState() => _WeatherScreenState();
}

class _WeatherScreenState extends State<WeatherScreen> {
  double temp = 0;
  
  Future<Map<String, dynamic>> getCurrentWeather() async{
    try {
      String cityName='Hyderabad,IN';
    final res = await http.get(
      Uri.parse('https://api.openweathermap.org/data/2.5/forecast?q=$cityName&APPID=$openWeatherAPIKey'),
      );
      final data = jsonDecode(res.body);
      if(data['cod'] != '200') {
        throw 'An Unexpected Error Occured';
      } 
      return data;
    } catch (e) {
      throw e.toString();
    }
  }

  @override
  Widget build(BuildContext context) {
    return  Scaffold(
      appBar: AppBar(
        title: const Text("Weather App", style: TextStyle(fontWeight: FontWeight.bold),),
        centerTitle: true,
        leading: Container(
          decoration: BoxDecoration(borderRadius: BorderRadius.circular(12)),
          margin: const EdgeInsets.all(8),
          alignment: Alignment.center,
          child: IconButton(onPressed: () {
            
              }, icon:const  Icon(Icons.light_mode_outlined)
            ),),
        actions:  [
          IconButton(onPressed: () {
            setState(() {});
              }, icon:const  Icon(Icons.refresh)
            ),
          ],
      ),
      body: FutureBuilder(
        future: getCurrentWeather(),
        builder: (context, snapshot ) {
          if(snapshot.connectionState==ConnectionState.waiting){
            return const Center(child: SpinKitRotatingCircle(color: Colors.white,size: 50.0,));
          }
          if (snapshot.hasError) {
            return Center(child: Text(snapshot.error.toString()));
          }
        final data=snapshot.data!;

        final currentWeatherData = data['list'][0];
        final currentTemp = currentWeatherData['main']['temp'];
        final currentSky = currentWeatherData['weather'][0]['main'];
        final currentHumidity = currentWeatherData['main']['humidity'];
        final currentPressure = currentWeatherData['main']['pressure'];
        final currentWindSpeed = currentWeatherData['wind']['speed'];
        final celsiusTemp = (currentTemp - 272.15);
        final temparature = celsiusTemp.toStringAsFixed(2);

          return Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
             children: [
              //main Card 
              SizedBox(
                width: double.infinity,
                child: Card(
                  shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(16)),
                  elevation: 10,
                  child: ClipRRect(
                    borderRadius: BorderRadius.circular(16),
                    child: BackdropFilter(
                      filter: ImageFilter.blur(sigmaX: 10, sigmaY: 10),
                      child: Padding(
                        padding: const EdgeInsets.all(16.0),
                        child: Column(
                          children: [
                            Text('$temparature° C',style: const TextStyle(fontSize: 32,fontWeight: FontWeight.bold,),),
                            const SizedBox(height: 16,),
                            Icon(
                              currentSky == 'Clouds' || currentSky == 'Rain'
                              ? Icons.cloud : Icons.sunny ,size: 64,),
                            const SizedBox(height: 16,),
                            Text(currentSky,style: const TextStyle(fontSize: 20),),
                          ],
                        ),
                      ),
                    ),
                  ),
                ),
              ),
              const SizedBox(height: 20,),
              const Text('Hourly Forecast',style: TextStyle(fontSize: 24,fontWeight: FontWeight.bold),),
              const SizedBox(height: 10,),
             SizedBox(
                height: 120,
                child: ListView.builder(
                  scrollDirection: Axis.horizontal,
                  itemCount: 5,
                  itemBuilder: (context, index) {
                    final hourlyForecast = data['list'][index+1];
                    final hourlyTemp = data['list'][index+1]['main']['temp'].toString();
                    final hourlySky = data['list'][index+1]['weather'][0]['main'];
                    final time = DateTime.parse(hourlyForecast['dt_txt']);
                    return HourlyForecastItem(
                      time: DateFormat.j().format(time),
                      icon: hourlySky == 'Clouds' || hourlySky == 'Rain' ? Icons.cloud : Icons.sunny, 
                      temp: '$hourlyTemp° K'
                      );
                  },
                  ),
              ),

              const SizedBox(height: 20,),
              //additional info
              const Text('Additional Information',style: TextStyle(fontSize: 24,fontWeight: FontWeight.bold),),
              const SizedBox(height: 12,),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  AdditionalInfoItem(
                    icon: Icons.water_drop,
                    label: 'Humidity',
                    value: currentHumidity.toString(),
                  ),
                  AdditionalInfoItem(
                    icon: Icons.air,
                    label: 'Wind Speed',
                    value: currentWindSpeed.toString(),
                  ),
                  AdditionalInfoItem(
                    icon: Icons.keyboard_double_arrow_down_rounded,
                    label: 'Pressure',
                    value: currentPressure.toString(),
                  ),
                ],
              ),
              const SizedBox(height: 30),
              const Center(child: Text('Hyderabad, IN'))
            ],
          ),
        );
        },
      ),
    );
  }
}



