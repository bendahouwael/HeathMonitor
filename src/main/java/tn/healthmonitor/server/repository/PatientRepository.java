package tn.healthmonitor.server.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import tn.healthmonitor.server.model.Patient;

import java.util.Optional;

public interface PatientRepository extends MongoRepository<Patient,Integer> {
    public Optional<Patient> getByCin(int id);
}
