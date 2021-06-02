package tn.healthmonitor.server.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import tn.healthmonitor.server.model.User;
import tn.healthmonitor.server.repository.UserRepository;

import java.util.List;

@RestController
@RequestMapping("api/User")
public class UserController {
    @Autowired
    private UserRepository userRepository;

    @GetMapping
    public List<User> getAll() {
        return userRepository.findAll();
    }

    @PostMapping
    public User create(@RequestBody User user)
    {
        return userRepository.save(user);
    }
    @GetMapping("/{cin}")
    public User getByCin(@PathVariable int cin)
    {
        return userRepository.getByCin(cin).orElse(new User("DoesNotExist"));
    }

}