package tn.healthmonitor.server.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import tn.healthmonitor.server.model.Patient;
import tn.healthmonitor.server.repository.PatientRepository;

import java.util.List;

@RestController
@RequestMapping("api/Patient")
public class PatientController {
    @Autowired
    private PatientRepository patientRepository;

    @GetMapping
    public List<Patient> getAll() {
        return patientRepository.findAll();
    }

    @PostMapping
    public Patient create(@RequestBody Patient patient)
    {
        return patientRepository.save(patient);
    }
    @GetMapping("/{cin}")
    public Patient getByCin(@PathVariable int cin)
    {
        return patientRepository.getByCin(cin).orElse(new Patient("DoesNotExist"));
    }

}