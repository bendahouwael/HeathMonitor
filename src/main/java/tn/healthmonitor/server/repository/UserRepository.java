package tn.healthmonitor.server.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import tn.healthmonitor.server.model.User;

import java.util.Optional;

public interface UserRepository extends MongoRepository<User,Integer> {
    public Optional<User> getByCin(int id);
}
