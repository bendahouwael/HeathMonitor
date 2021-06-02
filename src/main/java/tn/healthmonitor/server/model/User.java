package tn.healthmonitor.server.model;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.TypeAlias;
import org.springframework.data.mongodb.core.mapping.Document;

@Document("User")
@TypeAlias("User")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class User {
    @Id
    String cin ;
    String ipAddress;
    String name;
    String surName;
    public User(String cin,String str)
    {
        this.cin = cin ;

    }
    public User(String str)
    {
        this("0",str,str,str);
    }
}
