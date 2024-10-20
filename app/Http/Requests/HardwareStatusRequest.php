<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;

class HardwareStatusRequest extends FormRequest
{
    /**
     * Determine if the user is authorized to make this request.
     */
    public function authorize(): bool
    {
        return true;
    }

    /**
     * Get the validation rules that apply to the request.
     *
     * @return array<string, \Illuminate\Contracts\Validation\ValidationRule|array<mixed>|string>
     */
    public function rules(): array
    {
        return [
            "incident" => "required|string",
            "temperature" => "required|numeric",
            "humidity" => "required|numeric",
            "vibration_level" => "required|numeric",
            "moisture_level" => "required|numeric",
            "motion_level" => "required|boolean"
        ];
    }
}
