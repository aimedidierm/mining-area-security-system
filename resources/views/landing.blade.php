<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    @vite(['resources/css/app.css','resources/js/app.js'])
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <title>IoT based Mining Area Security System</title>
</head>

<body class="bg-gray-100">

    <header class="bg-blue-600 text-white py-6">
        <div class="container mx-auto text-center">
            <h1 class="text-4xl font-bold">IoT based Mining Area Security System</h1>
            <p class="mt-2 text-lg">Ensuring safety with innovative technology</p>
        </div>
    </header>

    <section class="py-12">
        <div class="container mx-auto px-4">
            <h2 class="text-3xl font-bold text-center mb-6">Key Features</h2>
            <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-8">

                <div class="bg-white rounded-lg shadow-lg p-6 text-center">
                    <span class="material-icons text-blue-600 text-5xl">vibration</span>
                    <h3 class="mt-4 text-xl font-semibold">Vibration Detection</h3>
                    <p class="mt-2">Detect vibrations and receive instant warnings for potential threats.</p>
                </div>

                <div class="bg-white rounded-lg shadow-lg p-6 text-center">
                    <span class="material-icons text-blue-600 text-5xl">visibility</span>
                    <h3 class="mt-4 text-xl font-semibold">Motion Detection</h3>
                    <p class="mt-2">Utilizes PIR sensors to detect movement, ensuring no activity goes unnoticed.</p>
                </div>

                <div class="bg-white rounded-lg shadow-lg p-6 text-center">
                    <span class="material-icons text-blue-600 text-5xl">water</span>
                    <h3 class="mt-4 text-xl font-semibold">Soil Moisture Detection</h3>
                    <p class="mt-2">DHT11 sensor monitors soil moisture, providing data to ensure optimal conditions.
                    </p>
                </div>

                <div class="bg-white rounded-lg shadow-lg p-6 text-center">
                    <span class="material-icons text-blue-600 text-5xl">data_usage</span>
                    <h3 class="mt-4 text-xl font-semibold">Data Monitoring</h3>
                    <p class="mt-2">Real-time data communication and monitoring accessible via a web interface.</p>
                </div>

                <div class="bg-white rounded-lg shadow-lg p-6 text-center">
                    <span class="material-icons text-blue-600 text-5xl">notifications</span>
                    <h3 class="mt-4 text-xl font-semibold">User Alerts</h3>
                    <p class="mt-2">LCD, LEDs, and buzzers provide immediate notifications of security events.</p>
                </div>

            </div>
        </div>
    </section>

    <section class="bg-blue-600 text-white py-8">
        <div class="container mx-auto text-center">
            <h2 class="text-3xl font-bold">Protect Your Mining Area Today!</h2>
            <p class="mt-4">Implement our IoT-based security system for peace of mind.</p>
            <a href="/login" class="mt-6 inline-block bg-white text-blue-600 font-semibold py-2 px-6 rounded-lg">Get
                Started</a>
        </div>
    </section>

    <footer class="bg-gray-800 text-white py-4">
        <div class="container mx-auto text-center">
            <p>&copy; 2024 IoT based Mining Security System. All rights reserved.</p>
        </div>
    </footer>

</body>

</html>