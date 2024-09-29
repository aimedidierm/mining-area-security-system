<?php

namespace App\Http\Controllers;

use App\Http\Requests\HardwareStatusRequest;
use App\Models\Hardware;

class HardwareController extends Controller
{
    /**
     * Display a listing of the resource.
     */
    public function index()
    {
        $data = Hardware::latest()->get();
        // return $data;
        return view('dashboard', compact('data'));
    }

    /**
     * Store a newly created resource in storage.
     */
    public function store(HardwareStatusRequest $request)
    {
        Hardware::create([
            "incident" => $request->input("incident"),
            "temperature" => $request->input("temperature"),
            "humidity" => $request->input("humidity"),
            "vibration_level" => $request->input("vibration_level"),
            "motion_level" => $request->input("motion_level"),
        ]);
    }

    /**
     * Display the specified resource.
     */
    public function show() {}
}
