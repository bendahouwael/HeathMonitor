package tn.healthmonitor.server.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import tn.healthmonitor.server.model.Patient;
import tn.healthmonitor.server.model.Payload;

import java.util.Date;
import java.util.List;

public interface PayloadRepository extends MongoRepository<Payload,String> {
    public List<Payload> getAllByPatient(Patient patient);

    public void deleteAllByCreationDateBefore(Date date);
}
