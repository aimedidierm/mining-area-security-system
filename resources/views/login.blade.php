<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    @vite(['resources/css/app.css','resources/js/app.js'])
    <title>Login - IoT based Mining Security System</title>
</head>

<body class="bg-gray-100 flex items-center justify-center min-h-screen">

    <div class="bg-white rounded-lg shadow-lg p-8 w-96">
        <h1 class="text-2xl font-bold text-center mb-6">Login</h1>
        <form method="POST" action="/auth/login">
            @if($errors->any())
            <span style="color: red;">{{$errors->first() }}</span>
            @endif
            @csrf
            <div class="mb-4">
                <label for="email" class="block text-sm font-semibold mb-2">Email</label>
                <input type="email" id="email" name="email" placeholder="Enter your email" required
                    class="w-full p-2 border border-gray-300 rounded-lg focus:outline-none focus:ring focus:ring-blue-200">
            </div>
            <div class="mb-6">
                <label for="password" class="block text-sm font-semibold mb-2">Password</label>
                <input type="password" id="password" name="password" placeholder="Enter your password" required
                    class="w-full p-2 border border-gray-300 rounded-lg focus:outline-none focus:ring focus:ring-blue-200">
            </div>
            <button type="submit"
                class="w-full bg-blue-600 text-white font-semibold py-2 rounded-lg hover:bg-blue-700 transition duration-200">
                Login
            </button>
        </form>
        <p class="mt-4 text-center text-sm text-gray-600">
            <a href="/" class="text-blue-600 hover:underline">Back home</a>
        </p>
    </div>

</body>

</html>