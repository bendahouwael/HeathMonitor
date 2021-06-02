package tn.healthmonitor.server.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.annotation.CreatedDate;
import org.springframework.web.bind.annotation.*;
import tn.healthmonitor.server.model.Payload;
import tn.healthmonitor.server.model.User;
import tn.healthmonitor.server.repository.PayloadRepository;

import java.util.Date;
import java.util.List;

@RestController
@RequestMapping("/api/Payload")
public class PayloadController {
    @Autowired
    private PayloadRepository payloadRepository;
   @GetMapping
    public List<Payload> getAll() {
        return payloadRepository.findAll();
    }

    @PostMapping
    public Payload create(@RequestBody Payload payload)
    { //Date d = new Date();
       payload.setCreationDate(new Date());

        return payloadRepository.save(payload);
    }
    @GetMapping("/{cin}")
    public List<Payload> getByUser(@PathVariable String cin)
    {
        User user = new User(cin);
        return payloadRepository.getAllByUser(user);
    }
    @DeleteMapping("/{date}")
    public void deleteBefore(@PathVariable Date date)
    {
        payloadRepository.deleteAllByCreationDateBefore(date);
    }
}